
/*------------------------------------------------------------------------------*/
/* users.h                                                                      */
/* copyright (c) innovaphone 2016                                               */
/*                                                                              */
/*------------------------------------------------------------------------------*/

typedef enum {
    USERS_PASSWORD_CHANGE_SUCCESS = 0,
    USERS_PASSWORD_CHANGE_PAM,
    USERS_PASSWORD_CHANGE_AUTHENTICATION,
    USERS_PASSWORD_CHANGE_ACCOUNT,
    USERS_PASSWORD_CHANGE_FAILURE
} users_password_change_error_t;

class IUsers {
public:
    static users_password_change_error_t ChangePassword(const char * user, const char * oldPassword, const char * newPassword);
};