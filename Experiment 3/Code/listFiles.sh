function listFiles()
{
        #1st param, the dir name
        #2nd param, the aligning space
        for file in `ls $1`;
        do
                if [ -d "$1/$file" ]; then
                    echo "$2$file"
                    listFiles "$1/$file" "    $2"
                else
                    echo "$2$file"
                fi
        done
}


path=`pwd`
listFiles $path ""
