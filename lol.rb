#!/usr/bin/ruby
# -*- coding: utf-8 -*-

load "String.rb"

room = []
density = []
ants = []
i = 0

system("rm -f ./err/*")
room[0] = 10
room[1] = 20
density[0] = 1
density[1] = 100
ants[0] = 10
ants[1] = 100
while (42)
  room[2] = (rand(10000)) % (2 + room[1].to_i - room[0].to_i) + room[0].to_i
  density[2] = (rand(10000)) % (5 + density[1].to_i - density[0].to_i) + density[0].to_i
  ants[2] = (rand(10000)) % (1 + ants[1].to_i - ants[0].to_i) + ants[0].to_i
  puts "Test #{i.to_s}, rooms = #{room[2].to_s}, density = #{density[2].to_s}, ants = #{ants[2].to_s}".bg_brown
  system("./generator.pl #{room[2]} #{density[2]} #{ants[2]} > tmp")
  system("cat tmp | ./lem_in | ./moulinette")
  if ($?.to_i == 0)
    puts "Test succeed !".bg_green
  elsif ($?.to_i == 2)
    exit 0
  else
    puts "Test failed !".bg_red
    system("mv tmp ./err/test#{i}")
  end
  i += 1
end
