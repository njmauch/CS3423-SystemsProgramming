#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#define ERR_EXIT 999

typedef struct
{
	char courseName[64];
	char courseSched[4];
	unsigned int courseHours;
	unsigned int courseSize;
} COURSE;

void create(int iFd);
void readRecord(int iFd);
void update(int iFd);
void deleteRecord(int iFd);
void errExit(const char szFmt[], ...);

int main(int argc, char *argv[])
{
	char *pszFileName = "courses.dat";
	char ch;
	int iFd;

	iFd = open(pszFileName, O_CREAT | O_RDWR);
	if (iFd < 0)
		errExit("Unable to open: %s", strerror(errno));

	printf("Enter one of the following actions or press CTRL-D to exit.\n");
	printf("C - create a new course record\n");
	printf("R - read an existing course record\n");
	printf("U - update an existing course record\n");
	printf("D - delete an existing course record\n");

	while (scanf(" %ch", &ch) != EOF)
	{
		switch (toupper(ch))
		{
		case 'C':
			create(iFd);
			break;
		case 'R':
			readRecord(iFd);
			break;
		case 'U':
			update(iFd);
			break;
		case 'D':
			deleteRecord(iFd);
			break;
		default:
			printf("ERROR: invalid option\n");
			break;
		}

		printf("Enter one of the following actions or press CTRL-D to exit.\n");
		printf("C - create a new course record\n");
		printf("R - read an existing course record\n");
		printf("U - update an existing course record\n");
		printf("D - delete an existing course record\n");
	}
	close(iFd);
}
void create(int iFd)
{
	int courseNumber;
	int lRBA, rcFseek;
	COURSE course;

	printf("Enter the course number: ");
	scanf("%d", &courseNumber);
	getchar();

	lRBA = courseNumber * sizeof(COURSE);
	rcFseek = read(iFd, &course, sizeof(COURSE));


	if (rcFseek > 0)
	{
		printf("ERROR: course already exists\n");
		return;
	}

	printf("Enter the course name: ");
	fgets(course.courseName, 64, stdin);
	printf("Enter the course schedule: ");
	fgets(course.courseSched, 4, stdin);
	printf("Enter the course credit hours: ");
	scanf("%d", &course.courseHours);
	getchar();
	printf("Enter the number of students enrolled: ");
	scanf("%d", &course.courseSize);
	getchar();

	write(iFd, &course, lRBA);

	return;
}
void readRecord(int iFd)
{
	COURSE course;
	int courseNumber;
	int lRBA, rcFseek, iRead;

	printf("Enter a CS course number: ");
	scanf("%d", &courseNumber);

	lRBA = courseNumber * sizeof(COURSE);
	rcFseek = lseek(iFd, lRBA, SEEK_SET);

	iRead = read(iFd, &course, sizeof(COURSE));

	if (iRead > 1)
	{
		printf("Course number: %d\n", courseNumber);
		printf("Course name: %s", course.courseName);
		printf("Schedule days: %s\n", course.courseSched);
		printf("Credit hours: %d\n", course.courseHours);
		printf("Enrolled Students: %d\n", course.courseSize);
	}
	else
		printf("ERROR: course not found\n");

	return;
}
void update(int iFd)
{
	COURSE course;
	int courseNumber;
	int lRBA, rcFseek, iWrite, iRead;
	char courseName[64];
	char courseSched[4];
	int courseHours;
	int courseSize;

	printf("Enter a CS course number: ");
	scanf("%d", &courseNumber);
	getchar();

	lRBA = courseNumber * sizeof(COURSE);
	rcFseek = lseek(iFd, lRBA, SEEK_SET);

	if (rcFseek != 0) {
		printf("ERROR: course not found\n");
		return;
	}

	iRead = read(iFd, &course, sizeof(COURSE));

	printf("Enter the course name: ");
	fgets(course.courseName, 64, stdin);
	printf("Enter the course schedule: ");
	fgets(course.courseSched, 4, stdin);
	printf("Enter the course credit hours: ");
	scanf("%d", &courseHours);
	getchar();
	printf("Enter the number of students enrolled: ");
	scanf("%d", &courseSize);
	getchar();

	if (courseName != NULL)
		strcpy(course.courseName, courseName);
	if (courseSched != NULL)
		strcpy(course.courseSched, courseSched);
	if (courseHours != NULL)
		course.courseHours = atoi(courseHours);
	if (courseSize != NULL)
		course.courseSize = atoi(courseSize);

	iWrite = write(iFd, &course, lRBA);

	return;
}
void deleteRecord(int iFd)
{
	COURSE course;
	int courseNumber;
	int lRBA, rcFseek, iWrite;

	printf("Enter a CS course number: ");
	scanf("%d", &courseNumber);
	getchar();

	lRBA = courseNumber * sizeof(COURSE);
	rcFseek = lseek(iFd, lRBA, SEEK_SET);

	if (rcFseek != 0)
		printf("ERROR: course not found\n");
	return;

	course.courseName[0] = '\0';
	course.courseSched[0] = '\0';
	course.courseHours = 0;
	course.courseSize = 0;

	iWrite = write(iFd, &course, lRBA);

	return;
}
void errExit(const char szFmt[], ...)
{
	va_list args;               // This is the standard C variable argument list type
	va_start(args, szFmt);      // This tells the compiler where the variable arguments
								// begins.  They begin after szFmt.
	printf("ERROR: ");
	vprintf(szFmt, args);       // vprintf receives a printf format string and  a
								// va_list argument
	va_end(args);               // let the C environment know we are finished with the
								// va_list argument
	printf("\n");
	exit(ERR_EXIT);
}
