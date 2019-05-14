#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import os

try:
    import requests
except ImportError:
    import sys
    sys.exit("Couldn't locate the requests module. Please install it! (try apt-get install python3-requests")

assistants = {'eriel18': 191,
              'samle75': 1379,
              'simke926': 619,
              'chrho44': 2451}
__course_code = 'TDP004'
__labs = [{'name': 'Enkel_IO'},
          {'name': 'Momstabell'},
          {'name': 'Kollisionshantering', 'given': 'git@gitlab.ida.liu.se:TDP004/Kollisionshantering.git'},
          {'name': 'Lista', 'given': 'git@gitlab.ida.liu.se:TDP004/Lista.git'},
          {'name': 'Trimino', 'given': 'git@gitlab.ida.liu.se:TDP004/Trimino.git'},
          {'name': 'Simulator'},
          {'name': 'Ordlista', 'given': 'git@gitlab.ida.liu.se:TDP004/Ordlista.git'},
          {'name': 'Pong', 'given': 'git@gitlab.ida.liu.se:TDP004/Pong.git'}]


class ParserHandler:
    """ Wrapper for an ArgumentParser together with subparsers """
    def __init__(self, parser_name: str):
        self.parser = argparse.ArgumentParser(parser_name)
        self.sp = self.parser.add_subparsers()
        self.all_parsers = {'main': self.parser}
        self.parser.set_defaults(selected_fun=self.display_help)
        sp = self.add_parser('help', help='Gives help on a specific tool. Usage: help <tool name> ')
        sp.add_argument('parser', nargs='?')
        sp.set_defaults(selected_fun=self.display_help)

    def display_help(self, args):
        parser = args.parser if 'parser' in vars(args) and args.parser in self.all_parsers else 'main'
        self.all_parsers[parser].print_help()

    def add_parser(self, name, *args, **kwargs):
        self.all_parsers[name] = self.sp.add_parser(name, *args, **kwargs)
        return self.all_parsers[name]


class GitlabAPI:
    """Home-written handler for the gitlab REST api"""

    __gitlab_token = os.path.expanduser('~/.config/gitlab_token')
    __gitlab_path = 'https://gitlab.ida.liu.se'

    def __init__(self, server=None):
        token = self.get_token()
        self.session = requests.Session()
        self.headers = {'PRIVATE-TOKEN': token, 'Accept': 'application/json'}
        self.session.headers = self.headers
        self.base_uri = (server or self.__gitlab_path) + '/api/v3/'
        self.user = self.user_info()

    def user_info(self, username=None):
        if not username:
            return self.session.get(self.base_uri + 'user', headers=self.headers).json()
        return self.session.get(self.base_uri + 'users', data={'username': username}, headers=self.headers).json()

    @property
    def uid(self):
        return self.user['id']

    @property
    def username(self):
        cas = self.user['identities']
        if cas:
            return cas[0]['extern_uid']
        return self.user['username']

    def my_groups(self):
        return self.session.get(self.base_uri + 'groups', headers=self.headers).json()

    def projects(self, group_id):
        data = self.session.get(self.base_uri + 'groups/{}'.format(group_id), headers=self.headers).json()
        if data:
            return data['projects']
        return None

    def create_group(self, name, members):
        data = {'name': name,
                'path': name.lower(),
                'visibility_level': 0}
        grp = self.session.post(self.base_uri + 'groups', data=data, headers=self.headers).json()
        if not grp:
            return None
        for u in members:
            if u['username'] != self.username:
                self.add_user_to_group(u['id'], grp['id'], 50)
        for username, uid in assistants.items():
            self.add_user_to_group(uid, grp['id'])
        return grp

    def add_user_to_group(self, uid, group_id, access=30):
        data = {'user_id': uid, 'access_level': access}
        uri = self.base_uri + 'groups/{}/members'.format(group_id)
        resp = self.session.post(uri, json=data, headers=self.headers)
        return resp.status_code == 201

    def create_project(self, group_id, name):
        tag_uri = 'https://appserv.ida.liu.se:12322/api/gitlab/tag_hook/'
        grp = self.session.get(self.base_uri + 'groups/{}'.format(group_id), headers=self.headers).json()
        if not grp:
            return None
        data = {'name': name,
                'namespace_id': group_id}
        project = self.session.post(self.base_uri + 'projects', json=data, headers=self.headers).json()
        if not project: return None
        data = {'url': tag_uri,
                'tag_push_events': True,
                'enable_ssl_verification': False,
                'push_events': False}
        resp = self.session.post(self.base_uri + 'projects/{}/hooks'.format(project['id']), json=data, headers=self.headers)
        if not resp:
            print("Couldn't setup tag, teachers will not be notified at updates!!")
        return project

    def get_token(self):
        token_path = GitlabAPI.__gitlab_token
        if not os.path.isfile(token_path):
            token = input('You must enter your gitlab API token. It can be found here {} (check for "private token"):'
                          .format('https://gitlab.ida.liu.se/profile/account'))
            with open(token_path, 'w') as f:
                f.write(token)
            os.chmod(token_path, 0o400)
        else:
            with open(token_path) as f:
                token = f.read().strip()
        return token


def create_group(session: GitlabAPI):
    users = [session.user_info()]
    new_user = input('Enter lab partner (leave empty if no partner): ')
    while new_user:
        gu = session.user_info(new_user.strip())
        if gu and len(gu) == 1:
            users.append(gu[0])
            break
        new_user = input("User {} doesn't exist. Enter new username: ")
    group_name = '{}-{}'.format(__course_code, '_'.join(sorted([u['username'] for u in users])))
    res = session.create_group(group_name, users)
    if not res:
        import sys
        sys.exit("Couldn't setup group. Exiting")
    return res


def register_project(pr, session):
    uri = 'https://appserv.ida.liu.se:12322/api/gitlab/group'
    headers = {'Accept': 'Application/json'}
    data = {'project_id': pr['id'],
            'gitlab_uid': session.uid,
            'uid': session.username,
            'course': __course_code}
    print('calling {} with'.format(uri))
    import pprint
    pprint.pprint(data)
    resp = requests.post(uri, json=data, headers=headers, verify=False)
    if resp.status_code == 201:
        return True
    else:
        print("Couldn't register project in server, got \n", resp.json())


def run_command(cmd, quiet=False, request_data=False, throw=False, *args, **kwargs):
    if args:
        cmd = [cmd]
        cmd += list(args)
    import subprocess
    if quiet and not request_data:
        for stream in ['stdout', 'stderr']:
            if stream not in kwargs:
                kwargs[stream] = subprocess.DEVNULL

    call_fun = subprocess.call
    if throw:
        call_fun = subprocess.check_call

    if request_data:
        if 'universal_newlines' not in kwargs:
            kwargs['universal_newlines'] = True
        kwargs['stderr'] = subprocess.STDOUT
        call_fun = subprocess.check_output

    try:
        return call_fun(cmd, **kwargs)
    except subprocess.CalledProcessError:
        if throw:
            raise
        return None


def git_command(args, directory=None, quiet=False, get_output=False):
    cmd = ['git']
    if directory:
        cmd.extend(['-C', directory])
    if isinstance(args, str):
        cmd.append(args)
    else:
        cmd.extend(args)
    return run_command(cmd, quiet, request_data=get_output)


def start(args):
    lab = list(filter(lambda l: l['name'] == args.lab, __labs))
    if not lab:
        import sys
        sys.exit('No lab named {} in this course'.format(args.lab))
    lab = lab[0]
    session = GitlabAPI()
    groups = session.my_groups()
    group_format = __course_code + r'-([a-z]{4,5}\d{2,3})(_([a-z]{4,5}\d{2,3}))?'
    group = None
    import re, os
    for g in groups:
        m = re.match(group_format, g['name'])
        if m and session.username in m.groups():
            group = g
            break
    group = group or create_group(session)
    projects = session.projects(group['id'])
    active_lab = list(filter(lambda p: p['name'].upper() == lab['name'].upper(), projects))
    created = False
    if not active_lab:
        print('Setting up new gitlab project')
        pr = session.create_project(group['id'], args.lab)
        if not register_project(pr, session):
            print('I will continue with setup, but please tell Eric that the last step failed')
            cont = input('Continue? [Y/n]: ').strip()
            if cont.upper() in ['N', 'NO']:
                import sys
                sys.exit()
        created = True
        active_lab.append(pr)

    base_path = os.path.expanduser('~/'+__course_code)
    path = os.path.join(base_path, args.lab)
    if not os.path.isdir(base_path):
        os.mkdir(base_path)
    elif os.path.isdir(path):
        import sys
        sys.exit("Directory {} exists, can't create new lab".format(path))
    project_url = active_lab[0]['ssh_url_to_repo']
    output = git_command(['clone', project_url, path], quiet=False, get_output=True).splitlines()
    if 'warning: You appear to have cloned an empty repository.' in output:
        given_path = lab.get('given')
        if given_path:
            remote_name = 'given'
            git_command(['remote', 'add', remote_name, given_path], path, quiet=True)
            git_command(['pull', remote_name, 'master'], path, quiet=True)
            git_command(['push', '-u', 'origin', 'master'], path, quiet=True)
        else:
            git_command(['commit', '--allow-empty', '-m', 'Empty project'], path, quiet=True)
            git_command(['push', '-u', 'origin', 'master'], path, quiet=True)
    print('Done, lab exists in directory', path)


def list_labs(_):
    print('Lab name')
    for l in __labs:
        print(l['name'])


def main():
    ph = ParserHandler('Lab setup')

    sp = ph.add_parser('start', help='Start a lab')
    sp.add_argument('lab', help='Name of the lab to start')
    sp.set_defaults(selected_fun=start)

    sp = ph.add_parser('list', help='List all labs')
    sp.set_defaults(selected_fun=list_labs)

    args = ph.parser.parse_args()
    args.selected_fun(args)

if __name__ == '__main__':
    main()
