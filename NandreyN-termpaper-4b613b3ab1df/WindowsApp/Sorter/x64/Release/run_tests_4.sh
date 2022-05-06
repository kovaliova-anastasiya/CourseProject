touch trash.txt
./Distributor 4 5 0 >> trash.txt
echo "4 5 0 result"
tail -1 trash.txt
rm trash.txt

touch trash.txt
./Distributor 4 10 0 >> trash.txt
echo "4 10 0 result"
tail -1 trash.txt
rm trash.txt

touch trash.txt
./Distributor 4 20 0 >> trash.txt
echo "4 20 0 result"
tail -1 trash.txt
rm trash.txt

touch trash.txt
./Distributor 4 50 0 >> trash.txt
echo "4 50 0 result"
tail -1 trash.txt
rm trash.txt