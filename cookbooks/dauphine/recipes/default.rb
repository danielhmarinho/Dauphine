#install packages to set environment and GUI.
execute 'apt-get update'
package 'vim'
package 'wget'
package 'git'
package 'libsdl2-image-dev'
package 'libsdl2-dev'
package 'libsdl2-mixer-dev'
package 'libsdl2-ttf-dev'
package 'libsdl2-gfx-dev'
package 'xfce4'
package 'libreadline-dev'
package 'g++'

#configure lua
execute 'wget lua' do
  command 'wget https://www.lua.org/ftp/lua-5.2.4.tar.gz -P /home/vagrant'
  not_if 'ls /home/vagrant/lua-5.2.4.tar.gz'
end

execute 'lua extract' do
  command 'tar -zxvf /home/vagrant/lua-5.2.4.tar.gz -C /home/vagrant'
  not_if 'ls /home/vagrant/lua-5.2.4'
end

execute 'change permission' do
  command 'chown -R vagrant:vagrant /home/vagrant/lua-5.2.4'
end

execute 'lua build' do
  command 'make linux test'
  cwd '/home/vagrant/lua-5.2.4/'
end

execute 'lua install' do
  command 'make linux install'
  cwd '/home/vagrant/lua-5.2.4/'
end

#configure dauphine
execute 'make dauphine' do
  command 'make'
  cwd '/vagrant/'
end
