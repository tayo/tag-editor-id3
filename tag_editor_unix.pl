#!/usr/bin/perl

use Getopt::Long;

open(LOGFILE, ">logfile.txt") || die("could not open log file\n");;
print LOGFILE "--logfile.txt---\n";
#	print("\nnumber of files processed: $num_processed\n");
#	print("number of files changed:   $num_changed\n");
#	print LOGFILE "\nnumber of files processed: $num_processed\n";
#	print LOGFILE "number of files changed:   $num_changed\n";

#$dirname = "/home/Kunle\ Oguntebi/tag_editor/mp3_files/";
$dirname = "/c/Files/Music/Rap\ R&B/Kanye\ West/";
print LOGFILE "about to recurse...\n";
&recurse($dirname);
close LOGFILE;

$num_processed = 0;
$num_changed = 0;


# recurse directory tree
sub recurse { 
	my ($path) = @_; 
	my $file;    #Variable for a file 

	opendir (DIRECTORY, $path) or die "cannot read $path\n"; 

	#Read all the files except for '.' and '..' 
	my @all_files = grep (!/^\.\.?$/, readdir (DIRECTORY)); 

	closedir (DIRECTORY); 

	foreach $file (@all_files) { 
		if (-d "$path$file/") { 
			&recurse("$path$file/"); 
		} else { 
			$num_processed++;
			print LOGFILE "\n---$path$file---\n";
			&rename($path, $file); 
#			&check_tag($path, $file);
		} 
	} 
} 

# tells whether every file in the directory has a tag or not
sub check_tag {
	($path, $file) = @_;
#	print("./tag -f \"$path$file\"\n");
	# check to see if there is an id3v2 tag
	system("./tag -v \"$path$file\"");
	if ($? == (2*256)) {
		print LOGFILE "found an id3v2 tag and deleted it\n"; }
	elsif ($? == (3*256)) {
		print LOGFILE "did not find an id3v2 tag\n"; }

	system("./tag -f \"$path$file\"");
	if ($? == (2*256)) {	# return status should equal 2 (this val / 256)
		print LOGFILE "found an id3v1 tag\n"; }
	else {
		print LOGFILE "did not find an id3v1 tag\n"; }
}

# turns all upper case characters into lowercase
sub rename {
	($path, $file) = @_;
	if ($file =~ tr/A-Z/a-z/) {
#		print LOGFILE "mv  \"$path$_[1]\" \"$file\"\n\n";
		print LOGFILE "renamed file to $file\n";
		system("mv \"$path$_[1]\" \"$file\"");
		$num_changed++;
	}
}
