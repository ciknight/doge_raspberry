apt-get install udhcpd hostapd

cp interfaces /etc/network
cp udhcpd.conf /etc/udhcpd.conf
cp hostapd.conf /etc/hostapd/hostapd.conf
sed -i 's/DHCPD_ENABLED="no"//g' /etc/default/udhcpd

# support RTL8188CUS
# lsusb  lsmod 
# use iw scan wifi-list
wget http://www.daveconroy.com/wp3/wp-content/uploads/2013/07/hostapd.zip
unzip hostapd.zip 
mv /usr/sbin/hostapd /usr/sbin/hostapd.bak
mv hostapd /usr/sbin/hostapd.edimax 
ln -sf /usr/sbin/hostapd.edimax /usr/sbin/hostapd 
chown root.root /usr/sbin/hostapd 
chmod 755 /usr/sbin/hostapd

ifconfig wlan0 192.168.42.1
sh -c "echo 1 > /proc/sys/net/ipv4/ip_forward"
sed -i 's/#net.ipv4.ip_forward=1/net.ipv4.ip_forward=1/g' /etc/sysctl.conf

iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
iptables -A FORWARD -i eth0 -o wlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT
iptables -A FORWARD -i wlan0 -o eth0 -j ACCEPT

sh -c "iptables-save > /etc/iptables.ipv4.nat"

echo 'up iptables-restore < /etc/iptables.ipv4.nat' >> /etc/network/interfaces

# reboot test hostapd
#hostapd -dd /etc/hostapd/hostapd.conf

echo 'DAEMON_CONF="/etc/hostapd/hostapd.conf"' >> /etc/default/hostapd

service hostapd start
service udhcpd start
update-rc.d hostapd enable
update-rc.d udhcpd enable
