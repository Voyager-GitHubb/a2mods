#!/usr/bin/env bash
# Anduril / FSM build wrapper script
# Copyright (C) 2017-2023 Selene ToyKeeper
# SPDX-License-Identifier: GPL-3.0-or-later

# Usage: build-all.sh [pattern]
# If pattern given, only build targets which match.

# enable "**" for recursive glob (requires bash)
shopt -s globstar



function main {

    if [ "$#" -gt 0 ]; then
        # multiple search terms with "AND"
        SEARCH=( "$@" )
        # memes
        [ "$1" = "me" ] && shift && shift && echo "Make your own $*." && exit 1
    fi



    # TODO: detect UI from $0 and/or $*
    UI=anduril

    mkdir -p hex

    make-version-h  # generate a version.h file



    PASS=0
    FAIL=0
    PASSED=''
    FAILED=''








<<K   # build targets are . . .

    OG: 
    # build targets are hw/$vendor/$model/**/$ui.h
    for TARGET in hw/*/*/**/"$UI".h ; do



    for TARGET in hw/*/*/**/"$UI".h ; do

    for TARGET in hw/*/*/**/"$UI".h ; do

D:\2025-A2\a2-r240420--385s--xui--\hw\sofirn\sc31-pro-t1616

\hw\sofirn\sc31-pro-t1616



\hw\sofirn--sc31-pro-t1616



    # OG:  # build targets are hw/$vendor/$model/**/$ui.h
    for TARGET in hw/*/*/**/"$UI".h ; do



    # Mod 01: build targets are hw/$vendor--$model/**/$ui.h
    for TARGET in hw/*--*/**/"$UI".h ; do

    # Mod 02: build targets are hw/*/**/$ui.h
    for TARGET in hw/*/**/"$UI".h ; do



    # Mod 03: build targets are hw/ . . . /$ui.h
    for TARGET in hw/**/"$UI".h ; do

    # Mod 04: build targets are hw/ . . . /$ui.h
    for TARGET in hw/*--*/"$UI".h ; do

    # Mod 05: build targets are hw/ . . . /$ui.h
    for TARGET in hw/*/"$UI".h ; do


K

<<K   # NOTE: build targets  "# Mod 04  is fastest   1 second or 2 seconds  

        ## NOTE: build targets search, build targets location . . . 
        echo '   '
        echo '  NOTE: build targets search, build targets location . . .  '
        echo '   '
        echo '  "# Mod 04: build targets are hw/ . . . /$ui.h"  '
        echo '  "for TARGET in hw/*--*/"$UI".h ; do ... "  '
        echo '   '
        echo '  "hw/*--*/"$UI".h" =  '
        echo "  " hw/*--*/"$UI".h "  "
        echo '   '

K

<<K   # NOTE: build targets  "# Mod 05  is fast   3 seconds  

        ## NOTE: build targets search, build targets location . . . 
        echo '   '
        echo '  NOTE: build targets search, build targets location . . .  '
        echo '   '
        echo '  "# Mod 05: "  '
        echo '  "for TARGET in hw/*/"$UI".h ; do ... "  '
        echo '   '
        echo '  "hw/*/"$UI".h" =  '
        echo "  " hw/*/"$UI".h "  "
        echo '   '

K

<<K   # NOTE: build targets  "# Mod 03  is slow  6 seconds  

        ## NOTE: build targets search, build targets location . . . 
        echo '   '
        echo '  NOTE: build targets search, build targets location . . .  '
        echo '   '
        echo '  "# Mod 03: build targets are hw/ . . . /$ui.h"  '
        echo '  "for TARGET in hw/**/"$UI".h ; do ... "  '
        echo '   '
        echo '  "hw/**/"$UI".h" =  '
        echo "  " hw/**/"$UI".h "  "
        echo '   '

K

<<K
    # Mod 10: build targets are hw/ . . . /$ui.h
    for TARGET in hw/*-*/"$UI".h ; do
K




    # Mod 10: build targets are hw/ . . . /$ui.h
    for TARGET in hw/*-*/"$UI".h ; do

        # friendly name for this build
        NAME=$(echo "$TARGET" | perl -ne 's|/|-|g; /hw-(.*)-'"$UI"'.h/ && print "$1\n";')

        # limit builds to searched patterns, if given
        SKIP=0
        if [ ${#SEARCH[@]} -gt 0 ]; then
            for text in "${SEARCH[@]}" ; do
                if ! echo "$NAME $TARGET" | grep -i -- "$text" > /dev/null ; then
                    SKIP=1
                fi
            done
        fi
        if [ 1 = $SKIP ]; then continue ; fi




        # announce what we're going to build
        echo "   "
        echo "   "
        echo "###   ###   ###   ###   ###   ###   ###   ###   ###   ###"
        echo "   "
        echo "   "
        echo "===== $UI $REV : $NAME ====="
        echo "   "


<<K
        ## NOTE: build targets search, build targets location . . . 
        echo '  '
        echo '  NOTE: build targets search, build targets location=  '
        # echo '  '
        echo '  "hw/*--*/"$UI".h" =  '
        echo "  " hw/*--*/"$UI".h "  "
        echo '  '
K




<<K

K



<<K         # The BUILDDATE

            ###########################################

            #  TRY THIS TIMEZONE AUTO CONVERSION  ...

            BUILDDATE=$( date -d '7 hours' '+%y%m%d.%H%M%S' )

            ###########################################

good format for file-name:  '+%y%m%d.%H%M%S'

K
            BUILDDATE=$( date -d '7 hours' '+%y%m%d.%H%M%S' )

        # try to compile, track result, and rename compiled files
        if bin/build.sh "$TARGET" ; then

            #  OG: HEX_OUT="hex/$UI.$NAME.hex"
            #  custom name options:
            #  HEX_OUT="hex/a2.250108.$NAME.hex"
            HEX_OUT="hex/a2.$BUILDDATE.$NAME.hex"


            #  OG: mv -f "ui/$UI/$UI".hex "$HEX_OUT"
            #  Mod : 
            mv -f "$UI/$UI".hex "$HEX_OUT"


            MD5=$(md5sum "$HEX_OUT" | cut -d ' ' -f 1)

            echo "   "
            echo "  # $MD5"
            echo "  > $HEX_OUT"

            echo "   "
            echo "  OK: $NAME build succeeded"


            # OG:
            PASS=$((PASS + 1))
            PASSED="$PASSED $NAME, "





        else

            echo "   "
            echo "  ERROR: build failed"

            FAIL=$((FAIL + 1))
            FAILED="$FAILED $NAME, "

        fi

    done



    # summary
    echo "   "
    echo "   "
    echo "###   ###   ###   ###   ###   ###   ###   ###   ###   ###"
    echo "   "
    echo "   "
    echo "===== $PASS builds succeeded, $FAIL failed ====="
    echo "   "
    echo "   "






<<K

###   ###   ###   ###   ###   ###   ###   ###   ###   ###
            # MOD:
            # PASS=$((PASS + 1))
            
            if PASS=1 ; then
                PASSED="$PASSED $NAME"

            else if PASS>1 ; then
            
                PASSED="$PASSED $NAME, "

###   ###   ###   ###   ###   ###   ###   ###   ###   ###

K






<<K

    if PASS=1 ; then
        PASSED="$PASSED $NAME"

    else if PASS>1 ; then
            
        PASSED="$PASSED $NAME, "
    fi



            # MOD:
            # PASS=$((PASS + 1))
            # PASSED="$PASSED $NAME"



            if PASS=1 ; then
                PASSED="$PASSED $NAME"

            elif PASS>1 ; then
            
                PASSED="$PASSED $NAME, "
            fi



K







    # PASS
    if [ 0 != $PASS ]; then

        echo "SUCCEEDED: $PASSED"
        echo "   "
        echo "   "

    fi



    # FAIL
    if [ 0 != $FAIL ]; then

        echo "FAILED   : $FAILED"
        echo "   "
        echo "   "

    fi



    # end / border
    echo "###   ###   ###   ###   ###   ###   ###   ###   ###   ###"
    echo "   "
    echo "   "
    echo "   "
    # echo "   "
    # echo "   "
    # echo "   "

    exit 1

}





function make-version-h {

    # old: version = build date
    #date '+#define VERSION_NUMBER "%Y-%m-%d"' > ui/$UI/version.h

    REV=$(bin/version-string.sh c)



<<K    # mkdir -p ".build/$UI"

    OG : 
    # save the version name to version.h
    mkdir -p ".build/$UI"
    echo '#define VERSION_NUMBER "'"$REV"'"' > ".build/$UI/version.h"

K

    ### 2025-01-18 Mod : 
    # save the version name to version.h
    mkdir -p ".build-$UI"
    echo '#define VERSION_NUMBER "'"$REV"'"' > ".build-$UI/version.h"

}


main "$@"








###   ###   ###   ###   ###   ###   ###   ###   ###

###   ###   ###   ###   ###   ###   ###   ###   ###

###   ###   ###   ###   ###   ###   ###   ###   ###

###   ###   ###   ###   ###   ###   ###   ###   ###

###   ###   ###   ###   ###   ###   ###   ###   ###

###   ###   ###   ###   ###   ###   ###   ###   ###

###   ###   ###   ###   ###   ###   ###   ###   ###

###   ###   ###   ###   ###   ###   ###   ###   ###




<<K

K




<<Kommentar

Kommentar




<<K   # MULTI-LINE COMMENTS IN A SHELL SCRIPT


   MULTI-LINE COMMENTS IN A SHELL SCRIPT

MULTI-LINE COMMENTS IN A SHELL SCRIPT

multi-line comments in a shell script

K




<<Kommentar

MULTI-LINE COMMENTS IN A SHELL SCRIPT

multi-line comments in a shell script

Kommentar




<<Kommentar   # MULTI-LINE COMMENTS IN A SHELL SCRIPT

MULTI-LINE COMMENTS IN A SHELL SCRIPT

multi-line comments in a shell script

Kommentar




<<Kommentar

:`  MULTI-LINE COMMENTS IN A SHELL SCRIPT


colon back-tick

back-tick


    # echo "///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///"

    ###  ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   

    ### "///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///"   

    ### "///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///"

###   ###   ###   ###   ###   ###   ###   ###   ###



###
   ###   


#
#

`


Kommentar








###   END   


