//
// Created by asgarov1 on 11/22/2020.
//

#include <string>
#include <iostream>
#include <ldap.h>

#include "LoginService.h"

using namespace std;

/**
 * connects to ldap and returns whether username and password combination allowed for successful login
 * @param username
 * @param password
 * @return bool - whether username and password allow to login
 */
bool LoginService::validateCredentials(const std::string& username, const std::string& password) {
    const char *ldapUri = "ldap://ldap.technikum-wien.at:389";
    const int ldapVersion = LDAP_VERSION3;

    int returnCode;
    LDAP *ldapHandle;

    returnCode = ldap_initialize(&ldapHandle, ldapUri);
    if (returnCode != LDAP_SUCCESS) {
        cerr << "ldap_init failed" << endl;
        return EXIT_FAILURE;
    }

    returnCode = ldap_set_option(
            ldapHandle,
            LDAP_OPT_PROTOCOL_VERSION,
            &ldapVersion
    );
    if (returnCode != LDAP_OPT_SUCCESS) {
        cerr << "ldap_set_option(PROTOCOL_VERSION): " << ldap_err2string(returnCode) << endl;
        ldap_unbind_ext_s(ldapHandle, nullptr, nullptr);
        return EXIT_FAILURE;
    }

    returnCode = ldap_start_tls_s(ldapHandle, nullptr, nullptr);
    if (returnCode != LDAP_SUCCESS) {
        cerr << "ldap_start_tls_s(): " << ldap_err2string(returnCode) << endl;
        ldap_unbind_ext_s(ldapHandle, nullptr, nullptr);
        return EXIT_FAILURE;
    }

    BerValue bindCredentials;
    bindCredentials.bv_val = (char *) password.c_str();
    bindCredentials.bv_len = password.length();
    BerValue *serverCredentials;
    string dn = "uid=" + username + ",ou=People,dc=technikum-wien,dc=at";
    returnCode = ldap_sasl_bind_s(ldapHandle,
                                  dn.c_str(),
                                  LDAP_SASL_SIMPLE,
                                  &bindCredentials,
                                  nullptr,
                                  nullptr,
                                  &serverCredentials);

    if (returnCode == LDAP_SUCCESS) {
        ldap_unbind_ext_s(ldapHandle, nullptr, nullptr);
        return true;
    } else {
        cerr << "LDAP bind error: " << ldap_err2string(returnCode) << endl;
        ldap_unbind_ext_s(ldapHandle, nullptr, nullptr);
        return false;
    }
}
