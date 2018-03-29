#!/bin/sh

./rshell.out

(echo this &&  mkdir new_folder) || (echo this should not work &&  rmdir new_folder)  || (rmdir new_folder && (rm file || echo this should output));

abort
