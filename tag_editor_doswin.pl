#!/usr/bin/perl 

#$dirname = "c:\\files\\music\\rock\\u2\\";
$dirname = "c:\\Files\\Temp\\";
$num_processed = 0;
$num_changed = 0;

open(LOGFILE, ">nocaps_logfile.txt") || die("could not open log file\n");;
&recurse($dirname);
print("\nnumber of files processed: $num_processed\n");
print("number of files changed:   $num_changed\n");
# print LOGFILE "\nnumber of files processed: $num_processed\n";
# print LOGFILE "number of files changed:   $num_changed\n";
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
		if (-d "$path$file\\") { 
			print("$path$file\n");
			my $cur_file = $file;
			if ($cur_file =~ tr/A-Z/a-z/) {
				print LOGFILE "ren \"$path$file\" \"$cur_file\"\n";
				#system("ren \"$path$file\" \"$path$cur_file\"\n");
				#system("ren \"$path$file\" \"$cur_file\"\n");
			}
			&recurse("$path$file\\"); 
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
		print LOGFILE "ren  \"$path$_[1]\" \"$file\"\n\n";
		#system("ren \"$path$_[1]\" \"$file\"");
		$num_changed++;
	}
}
