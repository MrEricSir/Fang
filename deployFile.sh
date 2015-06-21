#!/bin/bash
echo "Send a file to the server.
echo "Run: "
echo "     $ deployFile filename linkname
echo ""
echo "You will be asked for your password."

# Quit if any command fails.
set -e 
set -o pipefail

USERNAME=mrericsir_getfangdownload
FILENAME=$1
LINKNAME=$2

BASENAME=$(basename $FILENAME)
HOST="ssh.phx.nearlyfreespeech.net"

scp $FILENAME $USERNAME@$HOST:$BASENAME
ssh -l $USERNAME $HOST "ln $BASENAME $LINKNAME"
