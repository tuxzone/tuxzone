mkdir /mnt/ubuntu
mount /dev/sda3 /mnt/ubuntu

  cd /mnt/ubuntu && rm -rf ./sys ./proc ./dev ./old-root ./lib/firmware/*
  mkdir -p ./sys ./proc ./dev ./old-root
  mount -o move /sys ./sys
  mount -o move /proc ./proc
  mount -o move /dev ./dev
  cp /lib/firmware/* ./lib/firmware/
  ./sbin/pivot_root . ./old-root
  exec chroot . bash <dev/console >dev/console 2>&1

