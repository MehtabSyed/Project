
helpFunction()
{
	echo "Invalid arg" 
	exit 1 	
}
echo "1st arg"  $0
echo $1
echo $3
echo $4 
echo "passed dir" $2
while getopts "p:" opt
do
    case "${opt}" in
        p) pathname=${OPTARG};;
	?) helpFunction ;;
    esac
done
echo $pathname/echo.sh 
$pathname/echo.sh 
