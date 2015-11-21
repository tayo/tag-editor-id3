#!/usr/bin/perl

use Getopt::Long;

#$dirname = "/users/koogunte/tag_editor/mp3_files/";
$dirname = "/users/koogunte/music/";
&recurse($dirname);

$num_processed = 0;
$num_changed = 0;

#	open(LOGFILE, ">nocaps_logfile.txt") || die("could not open log file\n");;
#	print("\nnumber of files processed: $num_processed\n");
#	print("number of files changed:   $num_changed\n");
#	print LOGFILE "\nnumber of files processed: $num_processed\n";
#	print LOGFILE "number of files changed:   $num_changed\n";
#	close LOGFILE;

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
#			&rename($path, $file); 
			&check_tag($path, $file);
		} 
	} 
} 

# tells whether every file in the directory has a tag or not
sub check_tag {
	($path, $file) = @_;
#	print("./tag -f \"$path$file\"\n");
	system("./tag -f \"$path$file\"");
	if ($? == (2*256)) {		# return status should equal 2 (this val / 256)
		print("$file has a tag\n");
#		print("$path$file has a tag\n");
	}
	else {
		print("$file has no tag\n");
	}
}

# turns all upper case characters into lowercase
sub rename {
	($path, $file) = @_;
	if ($file =~ tr/A-Z/a-z/) {
		print LOGFILE "mv  \"$path$_[1]\" \"$file\"\n\n";
		system("mv \"$path$_[1]\" \"$file\"");
		$num_changed++;
	}
}
