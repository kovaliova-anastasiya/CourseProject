touch trash.txt
./Distributor 1 5 0 >> trash.txt
echo "1 5 0 result"
tail -1 trash.txt
rm trash.txt

touch trash.txt
./Distributor 1 10 0 >> trash.txt
echo "1 10 0 result"
tail -1 trash.txt
rm trash.txt

touch trash.txt
./Distributor 1 20 0 >> trash.txt
echo "1 20 0 result"
tail -1 trash.txt
rm trash.txt

touch trash.txt
./Distributor 1 50 0 >> trash.txt
echo "1 50 0 result"
tail -1 trash.txt
rm trash.txt