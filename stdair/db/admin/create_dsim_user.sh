#!/bin/sh
#
# Three parameters are optional:
# - the name of the database (on the MySQL server)
# - the host server of the database
# - the port of the database
#

# Database Name
DB_NAME="mysql"

# Database server (host)
DB_HOST="localhost"

# Database server port
DB_PORT="3306"

if [ "$1" != "" ]; then
	DB_NAME=$1
fi

if [ "$2" != "" ]; then
	DB_HOST=$2
fi 

if [ "$3" != "" ]; then
	DB_PORT=$3
fi


if [ "$1" = "--help" -o  "$1" = "-h" -o  "$1" = "-H" ]; then
	echo "Usage: $0 [ <Name of Database> <Host> <Port> ]"
	echo ""
	exit -1
fi

#
echo "Accessing MySQL database hosted on $DB_HOST:$DB_PORT to create database '${DB_NAME}'."
echo "To create a database, username and password of an administrator-like MySQL account"
echo "are required. On most of MySQL databases, the 'root' MySQL account has all"
echo "the administrative rights, but you may want to use a less-privileged MySQL"
echo "administrator account. Type the username of administrator followed by "
echo "[Enter]. To discontinue, type CTRL-C."
read userinput_adminname

echo "Type $userinput_adminname's password followed by [Enter]"
read -s userinput_pw

# Database user
DB_USER=${userinput_adminname}

# Database password
DB_PASSWD=${userinput_pw}

#
createDSimUser() {
	echo "Creating the DSim user within the database:"
	mysql -u ${DB_USER} --password=${DB_PASSWD} -P ${DB_PORT} -h ${DB_HOST} ${DB_NAME} < ${SQL_FILE}
	mysql -u ${DB_USER} --password=${DB_PASSWD} -P ${DB_PORT} -h ${DB_HOST} -e "flush privileges"
}

# Creating the DSim user
SQL_FILE="create_dsim_user.sql"
createDSimUser

