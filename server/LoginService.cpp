//
// Created by asgarov1 on 11/22/2020.
//

#include <string>
#include <iostream>
#include <ldap.h>
#include <sys/stat.h>
#include <dirent.h>

#include "LoginService.h"

bool LoginService::validateCredentials(std::string username, std::string password) {

//    TODO ldapsearch -h ldap.technikum-wien.at:389 -b "dc=technikum-wien, dc=at" -x -LLL -s sub -D
//     "uid=if19b003,ou=People,dc=technikum-wien,dc=at" -W password -ZZ "uid=if19b00*" uid cn

//        LDAP *ld;            /* LDAP resource handle */
//        LDAPMessage *result, *e;    /* LDAP result handle */
//        BerElement *ber;        /* array of attributes */
//        char *attribute;
//        BerValue **vals;
//
//        BerValue *servercredp;
//        BerValue cred;
//
//
//        char pw_char_array[pass.length() + 1];
//        strcpy(pw_char_array, pass.c_str());
//        cred.bv_val = (char *) pw_char_array;
//        cred.bv_len = pass.length();
//
//        int i, rc = 0;
//
//        const char *attribs[] = {"uid", "cn", NULL};        /* attribute array for search */
//
//        int ldapversion = LDAP_VERSION3;
//
//        /* setup LDAP connection */
//        if (ldap_initialize(&ld, LDAP_URI) != LDAP_SUCCESS) {
//            fprintf(stderr, "ldap_init failed");
//            return EXIT_FAILURE;
//        }
//
//        printf("connected to LDAP server %s\n", LDAP_URI);
//
//        if ((rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &ldapversion)) != LDAP_SUCCESS) {
//            fprintf(stderr, "ldap_set_option(PROTOCOL_VERSION): %s\n", ldap_err2string(rc));
//            ldap_unbind_ext_s(ld, NULL, NULL);
//            return EXIT_FAILURE;
//        }
//
//        if ((rc = ldap_start_tls_s(ld, NULL, NULL)) != LDAP_SUCCESS) {
//            fprintf(stderr, "ldap_start_tls_s(): %s\n", ldap_err2string(rc));
//            ldap_unbind_ext_s(ld, NULL, NULL);
//            return EXIT_FAILURE;
//        }
//
//        /* anonymous bind */
//
//        std::string bind_user_str = "uid=" + user + ",ou=People," + SEARCHBASE;
//        char bind_user[bind_user_str.length() + 1];
//        strcpy(bind_user, bind_user_str.c_str());
//        rc = ldap_sasl_bind_s(ld, bind_user, LDAP_SASL_SIMPLE, &cred, NULL, NULL, &servercredp);
//
//        if (rc != LDAP_SUCCESS) {
//            fprintf(stderr, "LDAP bind error: %s\n", ldap_err2string(rc));
//            ldap_unbind_ext_s(ld, NULL, NULL);
//            return false;
//        }
//        printf("bind successful\n");
//
//
//        printf("LDAP search suceeded\n");
//
//        ldap_unbind_ext_s(ld, NULL, NULL);
    return true;
}
