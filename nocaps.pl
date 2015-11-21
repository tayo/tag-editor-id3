#!/usr/bin/perl -w

$dirname = "/home/Kunle\ Oguntebi/Files/Music/";
$num_processed = 0;
$num_changed = 0;

open(LOGFILE, ">./nocaps_logfile.txt") || die("could not open log file\n");;
&recurse($dirname);
print("\nnumber of files processed: $num_processed\n");
print("number of files changed:   $num_changed\n");
print LOGFILE "\nnumber of files processed: $num_processed\n";
print LOGFILE "number of files changed:   $num_changed\n";
close LOGFILE;


# recurse directory tree
sub recurse { 
	my ($path) = @_; 
	my $file;    #Variable for a file 

	opendir (DIRECTORY, $path) or die "Can't read $path\n"; 

	#Read all the files except for '.' and '..' 
	my @all_files = grep (!/^\.\.?$/, readdir (DIRECTORY)); 

	closedir (DIRECTORY); 

	foreach $file (@all_files) { 
		if (-d "$path$file/") { 
			&recurse("$path$file/"); 
		} else { 
			$num_processed++;
			&rename($path, $file); 
		} 
	} 
} 

# turns all upper case characters into lowercase
sub rename {
	($path, $file) = @_;
	if ($file =~ tr/A-Z/a-z/) {
		print LOGFILE "from: \"$path$_[1]\"\n"; 
		print LOGFILE "to:   \"$path$file\"\n\n";
#		print LOGFILE "mv -f \"$path$_[1]\" \"$path$file\"\n\n";
		system("mv -f \"$path$_[1]\" \"$path$file\"");
		$num_changed++;
	}
}
