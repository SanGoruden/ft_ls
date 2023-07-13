#include "printing.h"

char get_file_type(mode_t file_mode)
{
    if (S_ISBLK(file_mode))
        return 'b';
    else if (S_ISCHR(file_mode))
        return 'c';
    else if (S_ISDIR(file_mode))
        return 'd';
    else if (S_ISLNK(file_mode))
        return 'l';
    else if (S_ISSOCK(file_mode))
        return 's';
    else if (S_ISFIFO(file_mode))
        return 'p';
    else
        return '-';
}

void get_file_permission(char *file_infos, mode_t file_mode)
{
    file_infos[1] = file_mode & S_IRUSR ? 'r' : '-';
    file_infos[2] = file_mode & S_IWUSR ? 'w' : '-';

    if (file_mode & S_IXUSR)
        file_infos[3] = file_mode & S_ISUID ? 's' : 'x';
    else
        file_infos[3] = file_mode & S_ISUID ? 'S' : '-';

    file_infos[4] = file_mode & S_IRGRP ? 'r' : '-';
    file_infos[5] = file_mode & S_IWGRP ? 'w' : '-';

    if (file_mode & S_IXGRP)
        file_infos[6] = file_mode & S_ISGID ? 's' : 'x';
    else
        file_infos[6] = file_mode & S_ISGID ? 'S' : '-';

    file_infos[7] = file_mode & S_IROTH ? 'r' : '-';
    file_infos[8] = file_mode & S_IWOTH ? 'w' : '-';

    if (file_mode & S_IXOTH)
        file_infos[9] = file_mode & S_ISVTX ? 't' : 'x';
    else
        file_infos[9] = file_mode & S_ISVTX ? 'T' : '-';
}

void get_type_and_permission(char *file_infos, mode_t file_mode)
{
    file_infos[0] = get_file_type(file_mode);
    get_file_permission(file_infos, file_mode);
}

void print_file_mode(struct stat file_stats)
{
    char infos[11];

    mode_t file_mode = file_stats.st_mode;
    get_type_and_permission(infos, file_mode);

    printf("%s ", infos);
    return ;
}

void print_username_or_id(struct stat file_stats)
{
    struct passwd *user_infos;

    if ((user_infos = getpwuid(file_stats.st_uid)) == NULL)
        printf("%d ", file_stats.st_uid);
    else
        printf("%s ", user_infos->pw_name);
}

void print_groupname_or_id(struct stat file_stats)
{
    struct group *group_infos;

    if ((group_infos = getgrgid(file_stats.st_gid)) == NULL)
        printf("%d ", file_stats.st_gid);
    else
        printf("%s ", group_infos->gr_name);
}

void print_last_modified_date(struct stat file_stats)
{
    time_t modified_time = file_stats.st_mtime;
    time_t now;
    time(&now);

    char **time_string = ft_split(ctime(&modified_time), ' ');
    char *year = ft_substr(time_string[4], 0, 4);
    char *month = time_string[1];
    char *day = time_string[2];
    char *hour_and_minute = ft_substr(time_string[3], 0, 5);
    //~2 630 000 seconds in a month
    if ((now - modified_time) < 2630000 * 6)
        printf("%2s %2s %5s ", month, day, hour_and_minute);
    else
        printf("%2s %2s %5s ", month, day, year);
}

void print_link_destination(struct stat file_stats, t_file_list *file)
{
    if (!S_ISLNK(file_stats.st_mode))
    {
        printf("\n");
        return;
    }

    char *buf = (char *)malloc(100 * sizeof(char));

    if (!buf)
    {
        perror("malloc");
        exit(1);
    }

    size_t size_read = readlink(file->path, buf, 100);
    buf[size_read] = '\0';
    printf(" -> %s\n", buf);
}

void print_total_blocks(t_file_list *file_list)
{
    if (!file_list)
        return;

    blkcnt_t    total_blocks = 0;
    struct stat file_stats;


    while (file_list)
    {

        if (lstat(file_list->path, &file_stats) == -1)
        {
            perror("stat");
            exit(1);
        }

        total_blocks += file_stats.st_blocks;

        file_list = file_list->next;
    }
    printf("total %lld\n", total_blocks);
}

void print_file_list(t_file_list *file_list, const char *path, uint8_t flags)
{
    if (flags & RECURSIVE)
        printf("\n%s:\n", path);
    if (flags & LONGLIST)
        print_total_blocks(file_list);
    
    struct stat file_stats;

    while (file_list)
    {

        if (lstat(file_list->path, &file_stats) == -1)
        {
            perror("stat");
            exit(1);
        }

        if (flags & LONGLIST)
        {
            print_file_mode(file_stats);
            printf("%2d ", file_stats.st_nlink);
            print_username_or_id(file_stats);
            print_groupname_or_id(file_stats);
            printf("%6lld ", file_stats.st_size);
            print_last_modified_date(file_stats);
        }
        printf("%s", file_list->file->d_name);
        if (flags & LONGLIST)
            print_link_destination(file_stats, file_list);
        else
            printf("\n");
        file_list = file_list->next;
    }
}