#!/usr/bin/perl -w

$path = "/home/Kunle\ Oguntebi/Files/Music/Rock/";

my $file;    #Variable for a file 

opendir (DIRECTORY, $path) or die "Can't read $path\n"; 

#Read all the files except for '.' and '..' 
my @all_files = grep (!/^\.\.?$/, readdir(DIRECTORY)); 

closedir (DIRECTORY); 

print("@all_files\n");

sub recurse {
	my $path = @_;

	foreach $file (@all_files) { 
		if (-d "$path$file/") { 
			print("directory $path$file\n");
			&recurse("$path$file/"); 
		} else { 
			print("$path$file\n\n");
		} 
	} 
}
