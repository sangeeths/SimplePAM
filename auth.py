from SimplePAM.libpam import validate
import argparse

def do_auth():
    parser = argparse.ArgumentParser()
    parser.add_argument('-u', '--username', help="enter username", required=True)
    parser.add_argument('-p', '--password', help="enter password", required=True)
    args = parser.parse_args()
    validate(args.username, args.password)

if __name__ == '__main__':
    do_auth()

# __END__
