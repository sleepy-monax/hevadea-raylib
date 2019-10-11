#define _XOPEN_SOURCE 500
#define __USE_XOPEN_EXTENDED

#include <ftw.h>
#include <assert.h>

#include <hevadea/utils.h>
#include <hevadea/filesystem.h>

static bool filesystem_iterate_nested = false;
static bool filesystem_iterate_stopped = false;
static filesystem_iterate_callback_t *filesystem_iterate_callback;
static void *filesystem_iterate_args;

int filesystem_iterate_native_callback(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    (void)sb;
    (void)ftwbuf;

    if (!filesystem_iterate_stopped)
    {
        filesystem_file_type_t type = FILESYSTEM_OTHER;

        if (typeflag == FTW_F)
        {
            type = FILESYSTEM_FILE;
        }
        else if (typeflag == FTW_D)
        {
            type = FILESYSTEM_DIRECTORY;
        }
        else if (typeflag == FTW_SL)
        {
            type = FILESYSTEM_LINK;
        }

        if (type != FILESYSTEM_OTHER)
        {
            if (filesystem_iterate_callback(fpath, type, filesystem_iterate_args) == ITERATION_STOP)
            {
                filesystem_iterate_stopped = true;
            }
        }
    }

    return 0;
}

void filesystem_iterate(const char *path, filesystem_iterate_callback_t *callback, void *args)
{
    assert(!filesystem_iterate_nested);

    filesystem_iterate_nested = true;
    filesystem_iterate_callback = callback;
    filesystem_iterate_args = args;

    nftw(path, filesystem_iterate_native_callback, 16, 0);

    filesystem_iterate_nested = false;
}