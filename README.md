SimplePAM
=========


A simple PAM module for authenticating user based on the following:
    -> /etc/passwd &amp; /etc/shadow 
    -> SQLite3 database files


We would need pam_sqlite3.so installed in order authenticate the 
users stored in the SQLite3 database file. To install pam_sqlite3.so, 
please follow the instructions in the following project.
    -> git@github.com:sangeeths/libpam-sqlite.git


The following are the configuration files:
    -> /etc/pam_sqlite.conf [for details, please refer 
       https://github.com/sangeeths/libpam-sqlite/blob/master/README_pam_sqlite3]
    -> /etc/pam.d/<service>
        

/etc/pam_sqlite.conf
--------------------
database = /home/sangeeth/SimplePAM/users.db
table = account
user_column = user_name
pwd_column = user_password
expired_column = acc_expired
newtok_column = acc_new_pwreq
debug = 1
pw_type = md5


/etc/pam.d/<service>
--------------------
auth        sufficient  pam_unix.so
auth        required    /lib/security/pam_sqlite3.so
account     required    /lib/security/pam_sqlite3.so
password    required    /lib/security/pam_sqlite3.so


Compilation
-----------

    $ make clean
    $ make


Usage
-----
Firstly, create a SQLite3 database file (users.db) and create a 
table (account) with the following columns.

    $ sqlite3 users.db
    sqlite> create table account(user_name varchar(25) primary key, user_password varchar(200), acc_expired varchar(3), acc_new_pwreq varchar(3));

To generate a password, please use gen_pwd.py program. It will 
generate SHA512 hash which can be used as a password.

    $ python gen_pwd.py
    Enter password: testing
    pwd = $6$xcV9LrGRTWkvSqzI$pd19v6ZvIeW/7pDi/iuSiGhXOxDVqvLn4A.uzvL8KOKizYDU7tNu4LnM8u68ySyKxYSh.bJuL99XpTUEKqPNn0
    $

Now populate the database (users.db) with one or more users records. 
Also add users to /etc/passwd and /etc/shadow which will be used for 
testing in the next step.

    sqlite> insert into account values('user1', '$6$xcV9LrGRTWkvSqzI$pd19v6ZvIeW/7pDi/iuSiGhXOxDVqvLn4A.uzvL8KOKizYDU7tNu4LnM8u68ySyKxYSh.bJuL99XpTUEKqPNn0', 'n', 'n');


Now to tests the PAM authentication, run auth.py with a username and password.

1. User present in /etc/passwd & /etc/shadow with valid password
    $ python auth.py -u sysuser -p password123
    sysuser successfully authenticated.
    $

2. User present in /etc/passwd & /etc/shadow but invalid password
    $ python auth.py -u sysuser -p invalidpwd
    Authentication failure [sysuser]
    $

3. User not present in /etc/passwd & /etc/shadow (and also not 
   present in the users.db)
    $ python auth.py -u invaliduser -p password
    User not known to the underlying authentication module [invaliduser]
    $

4. User not present in /etc/passwd & /etc/shadow but present 
   in the users.db with valid password
    $ python auth.py -u dbuser -p password123
    dbuser successfully authenticated.
    $

5. User not present in /etc/passwd & /etc/shadow but present 
   in the users.db but invalid password
    $ python auth.py -u dbuser -p invalidpwd
    Authentication failure [dbuser]
    $


__END__
