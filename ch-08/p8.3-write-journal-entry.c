/* p8.3-write-journal-entry.c
 * Write and Sync a Journal Entry
 */

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char* journal_filename = "journal.log";
void write_journal_entry(char* entry)
{
	int fd = open(journal_filename, O_WRONLY | O_CREAT | O_APPNED, 0660);
	write(fd, entry, strlen(entry));
	write(fd, "\n", 1);
	fsync(fd);
	close(fd);
}