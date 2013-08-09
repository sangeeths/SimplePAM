#include <security/pam_appl.h>
#include <security/pam_misc.h>

/* function prototypes */
int conversation(int, 
                 const struct pam_message **, 
                 struct pam_response **, 
                 void *);
int validate(char *, char *);
const char * _pam_error(int errcode);


int conversation(int msg_count, 
                 const struct pam_message **msg, 
                 struct pam_response **resp, 
                 void *pw)
{
    struct pam_response *r = NULL;
    int i = 0;
    
    if (msg_count <= 0 || msg_count > PAM_MAX_NUM_MSG)
        return PAM_CONV_ERR;

    if ((r = (struct pam_response *) calloc(msg_count, 
              sizeof(struct pam_response))) == NULL) 
        return PAM_BUF_ERR;
    
    for(i=0; i<msg_count; ++i) {
        r[i].resp_retcode = 0;
        r[i].resp = strdup(pw);
    }

    *resp = r;
    return PAM_SUCCESS;
}

int validate(char *un, char *pw)
{
    int retval;
    pam_handle_t *pamh = NULL;
    char *app_name = "testauth";
    struct pam_conv conv = {conversation, pw};

    if (!un || !pw) 
        return PAM_AUTH_ERR;
    
    retval = pam_start(app_name, un, &conv, &pamh);
    if (retval != PAM_SUCCESS) 
        return retval;

    retval = pam_authenticate(pamh, 0);
    if (retval != PAM_SUCCESS) 
        return retval;

    /*
    retval = pam_acct_mgmt(pamh, 0);
    if (retval == PAM_NEW_AUTHTOK_REQD) {
        if ((retval = pam_chauthtok(pamh, PAM_CHANGE_EXPIRED_AUTHTOK)) 
                    != PAM_SUCCESS) {
            return retval;
        }
    } else if (retval != PAM_SUCCESS) {
        return retval;
    }
    */

    retval = pam_end(pamh, retval);
    if (retval != PAM_SUCCESS) 
        return retval;

    return retval;
}

const char * _pam_error(int errcode)
{
    return pam_strerror(NULL, errcode);
}

int main(int agrc, char *argv[])
{
    /* I've got nothing to do!! */
    return 0;
}

/* __END__ */
