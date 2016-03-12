cd latency
make clean all
cd objs/armv6vfphLinux3.xgcc4.7.2/
scp latency_host latency_echo pi@pi06:~/
ssh pi@pi06 './latency_host 4 > rti_host.log &' './latency_echo 3 > rti_echo.log' 'sudo killall latency_host'
sleep 1
#ssh pi@pi06 'killall latency_host'
scp pi@pi06:~/rti_*.log .
ssh pi@pi06 'rm latency_host latency_echo'
echo ""
echo "=== Host ==="
echo ""
cat rti_host.log
echo ""
echo "=== ECHO ==="
echo ""
cat rti_echo.log

