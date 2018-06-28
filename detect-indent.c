#include <stdio.h>

// Should print an integer: number of spaces / 0 for tabs
// In case of error, just guess 4
int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("4");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == NULL) {
		printf("4");
		return 1;
	}

	char line[80];
	// We will process at most 79 characters of each line

        int line_num = 0;
        int num_lines_with_tabs = 0;

        unsigned short int num_spaces[1000];
        // We will process at most 1000 lines

        for (int i = 0; i < 1000; i++)
		num_spaces[i] = 0;

	for (line_num = 0; line_num < 1000 && !feof(fp); line_num++) {
		fgets(line, 80, fp);
		for (int i = 0; i < 80; i++) {
			switch (line[i]) {
				case '\0':
				case '\n':
					goto next_line;

			        case '\t':
			                num_spaces[line_num] = -1;
			                num_lines_with_tabs++;
			                break;

		                case ' ':
		                        num_spaces[line_num]++;
		                        break;

	                        default:
					goto next_line;
			}
		}
	next_line:
		continue;
	}

	int num_indented_lines = 0;
        for (int i = 0; i < line_num; i++) {
	        if (num_spaces[i] != 0) {
		        num_indented_lines++;
	        }
        }

	if (num_lines_with_tabs > num_indented_lines / 2) {
		printf("0");
	} else {
		// Assume the indent size is between 2 and 8
		// Find the Highest one which fits >80% of lines

		for (int i = 8; i >= 2; i--) {
			int num_ok = 0;
			for (int j = 0; j < line_num; j++) {
				if (num_spaces[j] > 0 && num_spaces[j] % i == 0) {
					num_ok++;
				}
			}

			if (num_ok > num_indented_lines * 0.8) {
				printf("%d", i);
				return 0;
			}
		}

		// Default case, just guess 2
		printf("2");
	}

	fclose(fp);

	return 0;
}
