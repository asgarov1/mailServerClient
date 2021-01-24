# Mail Server Client

**by** *Javid Asgarov<br/> 
**&** Agnaldo Oliveira Moura Junior*

## To run: 
first run **cmake ./** and then **make all**

after that you can run 
* 1 mailserver: **./mailserver [port] [path to mail folder]**
* many clients: **./mailclient [ip address] [port]**


## To compile:

You will need to have the following packages installed:
* for Ubuntu/Debian: **libldap2-dev**
* for Fedora: **openldap-devel**

ps: apparently there are potential zombie issues and mutexes don´t always work. Would need to be taken a look at before reuse.
