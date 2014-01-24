# For testing the reading of db tables.
import psycopg2
import time
import sys
import string

airTemp = 22
humidity = 58
phValue = 6

def main(*args, **kwargs):
    dbConnection = psycopg2.connect(host = "web377.webfaction.com",
                                    database = "hydrodata",
                                    user = "pydroponics",
                                    password = "AutoHydro")

        
    dbCursor = dbConnection.cursor()
    argList = [time.strftime("%m/%d/%Y %H:%M:%S", time.localtime()),]
    commandString = "INSERT INTO " + kwargs.get('updateTable') + " VALUES (%s"
    for count, value in enumerate(args):
        argList.append(value)
        commandString += ", %s"
    commandString += ")"
    print commandString
    print argList
    dbCursor.execute(commandString, argList)
    dbConnection.commit()
    dbCursor.close()

if __name__ == "__main__":
    main(airTemp,humidity, updateTable = 'atmosphere')
