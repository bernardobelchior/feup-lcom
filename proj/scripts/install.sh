cd ..
cp conf/proj /etc/system.conf.d
mkdir /home/proj
#cp -vr res/ /home/proj
cp -vr cfg/ /home/proj
chmod 777 scripts/compile.sh
chmod 777 scripts/run.sh
