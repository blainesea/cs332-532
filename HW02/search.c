#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

/* defining function ptr to print details when -v is used */
typedef void (*PrintDetailsFunction)(const char *, const struct stat *);

/* function to print details when -v is used  */
void printDetailsDefault(const char *filename, const struct stat *info) {
    printf("%s (size: %ld bytes, permissions: %o, last access: %s)\n", filename, (long)info->st_size,
           info->st_mode & 0777, ctime(&info->st_atime));
}

/* function ptr to print details for -v */
PrintDetailsFunction printDetailsFunction = printDetailsDefault;

/* ensures file meets criteria for -L or -s command line options  */
int matchCriteria(const char *filename, const struct stat *info, off_t sizeLimit, const char *pattern, int depthLimit) {
    /* checking if file size is > 0 and if it exceeds the size limit */
    if (sizeLimit > 0 && info->st_size > sizeLimit) {
        return 0; /* file does not meet criteria  */
    }

    /* checking if filename contains given pattern */
    if (pattern != NULL && strstr(filename, pattern) == NULL) {
        return 0; /* file does not meet criteria  */
    }


    return 1; /* file meets criteria! */
}

/* printing files inside directory recursively */
void printDirectory(const char *dirname, int depth, int showDetails, off_t sizeLimit, const char *pattern, int depthLimit, PrintDetailsFunction printDetails) {
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    
    /* open directory */
    if ((dir = opendir(dirname)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    /* printing file name w/ correct indentation */
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }

    /* getting directory name */
    const char *lastPathComponent = strrchr(dirname, '/');
    const char *dirnameToPrint = (lastPathComponent != NULL) ? lastPathComponent + 1 : dirname;

    /* printing directory name or details */
    if (showDetails) {
        if (lstat(dirname, &info) == -1) {
            perror("lstat");
            exit(EXIT_FAILURE);
        }
        printDetails(dirnameToPrint, &info);
    } else {
        printf("%s/\n", dirnameToPrint);
    }

    /* traversing all directories/files */
    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        if (lstat(path, &info) == -1) {
            perror("lstat");
            exit(EXIT_FAILURE);
        }

        /* recursively printing the files in the directory */
        if (S_ISDIR(info.st_mode)) {
            /* avoiding . and .. for infinite loops */
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                printDirectory(path, depth + 1, showDetails, sizeLimit, pattern, depthLimit, printDetails);
            }
        } else { /* printing files */
            for (int i = 0; i < depth + 1; i++) {
                printf("\t");
            }

            if (showDetails) {
                printDetails(entry->d_name, &info);
            } else {
                /* printing symbolic link if present */
                if (S_ISLNK(info.st_mode)) {
                    char linkname[1024];
                    ssize_t len = readlink(path, linkname, sizeof(linkname) - 1);
                    if (len != -1) {
                        linkname[len] = '\0';
                        printf("%s (-> %s)\n", entry->d_name, linkname);
                    } else {
                        perror("readlink");
                        exit(EXIT_FAILURE);
                    }
                } else {
                    /* checking depth limit and match criteria */
                    if (depthLimit < 0 || depth + 1 <= depthLimit) {
                        if (matchCriteria(entry->d_name, &info, sizeLimit, pattern, depthLimit)) {
                            printf("%s\n", entry->d_name);
                        }
                    }
                }
            }
        }
    }

    closedir(dir);
}

/* initiating the search */
void search(const char *dirname, int depth, int showDetails, off_t sizeLimit, const char *pattern, int depthLimit) {
    /* passing the function ptr to printDetailsFunction */
    printDirectory(dirname, depth, showDetails, sizeLimit, pattern, depthLimit, printDetailsFunction);
}

/* main function: 
handles the different command line options using getopt( */
int main(int argc, char *argv[]) {
    /* default directory for traversal */
    const char *dirname = ".";
    /* var used later to determine if file details should be printed*/
    int showDetails = 0; 
    /* empty var for file size limit */
    off_t sizeLimit = 0;        
    /* pattern to match file names */
    const char *pattern = NULL;
    /* depth limit for traversing files */
    int depthLimit = -1;
    int c;

    /* using getopt to parse thru command line options */
    while ((c = getopt(argc, argv, "vL:s:")) != -1) {
        /* switch cases for command line options -v, -L and -s  */
        switch (c) {
            /* More Details */
            case 'v':
                printDetailsFunction = printDetailsDefault;
                showDetails = 1;
                break;
            /* Large Files */
            case 'L':
                sizeLimit = atoll(optarg);
                break;
            /* String pattern and depth */
            case 's':
                pattern = optarg;
                depthLimit = atoi(argv[optind++]);
                break;
            /* erorr handling for unexpected inputs */
            case '?':
                if (optopt == 'L' || optopt == 's') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option -%c.\n", optopt);
                }
                return 1;
            default:
                /* aborting if a diff argument is passed in */
                abort();
        }
    }

    /* if there are more args, sets correct directory name */
    if (optind < argc) {
        dirname = argv[optind];
    }

    /* calling to search function, traverses directories and lists out files */
    search(dirname, 0, showDetails, sizeLimit, pattern, depthLimit);

    return 0;
}

