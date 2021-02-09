

# 来源 每天5分钟 openstack  1.5.1 linux_bridge


# brctl

## brctl show


````
[root@ossdbg1_ccn2 bin]# brctl show
bridge name     bridge id               STP enabled     interfaces
docker0         8000.0242a5177587       no              veth23828ba
                                                        veth2b74243
                                                        veth2baf96b
                                                        veth2dcb401
                                                        veth34552d0
                                                        veth79c8223
                                                        veth940220c
                                                        vethae6065b
                                                        vethdc3e7d6
                                                        vethe17cce5
                                                        vethfd2b2aa
virbr0          8000.52540091cbbe       yes             virbr0-nic




# ifconfig
virbr0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 192.168.122.1  netmask 255.255.255.0  broadcast 192.168.122.255
        ether 52:54:00:91:cb:be  txqueuelen 0  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0


docker0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.172.0.1  netmask 255.255.0.0  broadcast 0.0.0.0
        inet6 fe80::42:a5ff:fe17:7587  prefixlen 64  scopeid 0x20<link>
        ether 02:42:a5:17:75:87  txqueuelen 0  (Ethernet)
        RX packets 14278758  bytes 7221591593 (6.7 GiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 15169181  bytes 7052646669 (6.5 GiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0




[root@ossdbg1_ccn2 bin]# ps -elf |grep dnsmasq
5 S nobody     9444      1  0  80   0 -  3898 poll_s  2020 ?        00:00:00 /sbin/dnsmasq --conf-file=/var/lib/libvirt/dnsmasq/default.conf --leasefile-ro --dhcp-script=/usr/libexec/libvirt_leaseshelper
1 S root       9445   9444  0  80   0 -  3891 pipe_w  2020 ?        00:00:00 /sbin/dnsmasq --conf-file=/var/lib/libvirt/dnsmasq/default.conf --leasefile-ro --dhcp-script=/usr/libexec/libvirt_leaseshelper
0 S root     210403 146825  0  80   0 - 28161 pipe_w 06:37 pts/4    00:00:00 grep --color=auto dnsmasq
[root@ossdbg1_ccn2 bin]#
[root@ossdbg1_ccn2 bin]# cat /var/lib/libvirt/dnsmasq/default.conf
##WARNING:  THIS IS AN AUTO-GENERATED FILE. CHANGES TO IT ARE LIKELY TO BE
##OVERWRITTEN AND LOST.  Changes to this configuration should be made using:
##    virsh net-edit default
## or other application using the libvirt API.
##
## dnsmasq conf file created by libvirt
strict-order
pid-file=/var/run/libvirt/network/default.pid
except-interface=lo
bind-dynamic
interface=virbr0
dhcp-range=192.168.122.2,192.168.122.254
dhcp-no-override
dhcp-lease-max=253
dhcp-hostsfile=/var/lib/libvirt/dnsmasq/default.hostsfile
addn-hosts=/var/lib/libvirt/dnsmasq/default.addnhosts
[root@ossdbg1_ccn2 bin]#


`````
