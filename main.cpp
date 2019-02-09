#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "main.h"
#include "config.h"



int
main (int argc, char **argv)
{
  /* Flag set by ‘--verbose’. */
  static int verbose_flag;
  static int help_flag;
  static bool show_help;
  int c;

  while (1)
    {
      static struct option long_options[] =
        {
          /* These options set a flag. */
          {"verbose", no_argument,       &verbose_flag, 1},
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"phone", required_argument,  0,  'u'},
          {"config",  required_argument,  0,  'c'},
          {"profile", optional_argument,  0,  'p'},
          {"exec",  required_argument,  0,  'e'},
          {"enable-msg-id", no_argument,  0,  'N'},
          {"disable-colors", no_argument, 0,  'C'},
          {"alert", no_argument,  0,  'A'},
          {"help", no_argument, 0,  'h'},
          //{"daemonize", no_argument,  0,  'd'},
          #ifdef USE_JSON
          {"json",     no_argument,       0, 'j'},
          #endif

          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;

      opterr = 0; // disable getopt error message
      c = getopt_long (argc, argv, ":hACNr:p:c:u:e:;",    // all short flags together
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'h':
        show_help = true;
          break;

        case 'A':
          puts ("option -b\n");
          break;

        case 'C':
          printf ("option -c with value `%s'\n", optarg);
          break;

        case 'N':
          printf ("option -d with value `%s'\n", optarg);
          break;

        case 'r':
          printf ("option -f with value `%s'\n", optarg);
          break;
        case 'p':
          if (optarg != NULL) {
            // set profile = optarg
          } else {
            // set profile = "default"
          }
          break;
        case 'c':
          break;
        case 'u':
          break;
        case'e':
          break;

        case '?': // invalid option
          printf("%s: invalid option -- '%c'\n", PACKAGE_NAME, optopt);
          help();
          break;
        case ':':   // missing option argument
          printf("%s: missing argument -- '%c'\n", PACKAGE_NAME, optopt);
          help();
          break;
        default:
          puts("arborting");
          abort ();
        }
    }
  if (verbose_flag)
    puts ("verbose flag is set");

  if (show_help)
    help();

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }

  exit (0);
}



static void help() {
  printf ("Usage: %s [options]\n", PACKAGE_NAME);
  
  printf ("  -u, --phone                    specify username (for registration)\n");
  printf ("  --verbose                      set to verbose mode\n");
  printf ("  -N, --enable-msg-id            message num mode\n");
  printf ("  -c, --config                    config file name\n");
  printf ("  -p, --profile                  use specified profile\n");
  printf ("  -C, --disable-colors           disabled colored output\n");
  printf ("  -A, --alert                    enable bell notifications\n");
  printf ("  -e, --exec                     execute a single command and exit\n");  //TODO: think about executing all non flag arguments
  #ifdef USE_JSON
  printf ("  -j, --json                     prints answers and values in json format\n");
  #endif

  //  further info
  puts("\n");
  printf("please report bugs at: %s", PACKAGE_BUGREPORT);


  exit (0);
}
