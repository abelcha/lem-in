#!/usr/bin/ruby
# -*- coding: utf-8 -*-

load "String.rb"

room = []
density = []
ants = []
i = 0

system("rm -f ./err/*")
print "Choose the smallest value of rooms : "
room[0] = gets.to_i.abs
print "Choose the biggest value of rooms : "
room[1] = gets.to_i.abs
print "Choose the smallest value of density : "
density[0] = gets.to_i.abs
print "Choose the biggest value of density : "
density[1] = gets.to_i.abs
print "Choose the smallest value of ants : "
ants[0] = gets.to_i.abs
print "Choose the biggest value of ants : "
ants[1] = gets.to_i.abs
while (42)
  room[2] = (rand(10000)) % (2 + room[1].to_i - room[0].to_i) + room[0].to_i
  density[2] = (rand(10000)) % (5 + density[1].to_i - density[0].to_i) + density[0].to_i
  ants[2] = (rand(10000)) % (1 + ants[1].to_i - ants[0].to_i) + ants[0].to_i
  puts "Test #{i.to_s}, rooms = #{room[2].to_s}, density = #{density[2].to_s}, ants = #{ants[2].to_s}".bg_brown
  system("./generator.pl #{room[2]} #{density[2]} #{ants[2]} > tmp")
  system("cat tmp | ./lem_in")
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
