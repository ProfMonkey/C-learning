#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUBJECT_COUNT 4

struct Student
{
    char id[16];
    char name[32];
    double scores[SUBJECT_COUNT];
    double average;
};

double highest_score(const struct Student *student)
{
    double best_score = student->scores[0];

    for (size_t i = 1; i < SUBJECT_COUNT; i++)
    {
        if (student->scores[i] > best_score)
        {
            best_score = student->scores[i];
        }
    }

    return best_score;
}

double calculate_average(const struct Student *student)
{
    double sum = 0.0;

    for (size_t i = 0; i < SUBJECT_COUNT; i++)
    {
        sum += student->scores[i];
    }

    return sum / (double)SUBJECT_COUNT;
}

int parse_student(const char *line, struct Student *out)
{
    char buffer[100];

    strcpy(buffer, line);

    const char *separators = ",\r\n";

    char *id_text = strtok(buffer, separators);
    char *name_text = strtok(NULL, separators);

    if (id_text == NULL || name_text == NULL)
    {
        return 0;
    }

    for (size_t i = 0; i < SUBJECT_COUNT; i++)
    {
        char *score_text = strtok(NULL, separators);

        if (score_text == NULL)
        {
            return 0;
        }

        char *end = NULL;
        double score = strtod(score_text, &end);

        if (end == score_text ||
            *end != '\0' ||
            score < 0.0 ||
            score > 100.0)
        {
            return 0;
        }

        out->scores[i] = score;
    }

    if (strtok(NULL, separators) != NULL)
    {
        return 0;
    }

    strcpy(out->id, id_text);
    strcpy(out->name, name_text);

    out->average = calculate_average(out);

    return 1;
}

int count_passed_subjects(const struct Student *student)
{
    int number = 0;

    for (size_t i = 0; i < SUBJECT_COUNT; i++)
    {
        if (student->scores[i] >= 60.0)
        {
            number++;
        }
    }

    return number;
}

int calculate_rank(const struct Student all_students[],
                   size_t student_count,
                   size_t target_index)
{
    int rank = 1;

    for (size_t other_index = 0;
         other_index < student_count;
         other_index++)
    {
        if (all_students[other_index].average >
            all_students[target_index].average)
        {
            rank++;
        }
    }

    return rank;
}

char get_grade(double average)
{
    if (average >= 90.0)
    {
        return 'A';
    }
    else if (average >= 80.0)
    {
        return 'B';
    }
    else if (average >= 70.0)
    {
        return 'C';
    }
    else if (average >= 60.0)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}

int main(void)
{
    const char *lines[] = {
        "20260023,Wang Fang,95,88,91.5,99",
        "20260044,Chen Yu,88,90,87.5,98",
        "20260052,Sun Na,70,92,81,97",
        "20260077,Bad Data,80,90",
        "20260088,Wrong Score,75,abc,88,90",
        "20260099,Out Range,75,101,88,90"
    };

    size_t line_count = sizeof lines / sizeof lines[0];

    struct Student students[sizeof lines / sizeof lines[0]] = {0};

    size_t student_count = 0;

    for (size_t line_index = 0;
         line_index < line_count;
         line_index++)
    {
        if (parse_student(lines[line_index],
                          &students[student_count]))
        {
            student_count++;
        }
        else
        {
            printf("Skipped invalid line: %s\n",
                   lines[line_index]);
        }
    }

    if (student_count == 0)
    {
        printf("No valid student records.\n");
        return 1;
    }

    size_t best_index = 0;
    size_t lowest_index = 0;
    size_t hardest_subject = 0;
    int count = 0;
    int all_pass_count = 0;
    double sum = 0.0;
    double subject_sums[SUBJECT_COUNT] = {0.0};

    for (size_t i = 0; i < student_count; i++)
    {
        int passed_subjects = count_passed_subjects(&students[i]);
        double highest = highest_score(&students[i]);
        int rank = calculate_rank(students, student_count, i);
        char grade = get_grade(students[i].average);

        printf("%s: rank %d, average %.2f, grade %c, "
               "highest score %.2f, passed subjects: %d\n",
               students[i].name,
               rank,
               students[i].average,
               grade,
               highest,
               passed_subjects);

        sum += students[i].average;

        if (students[i].average >= 85.0)
        {
            count++;
        }

        if (students[i].average > students[best_index].average)
        {
            best_index = i;
        }

        if (students[i].average < students[lowest_index].average)
        {
            lowest_index = i;
        }

        if (passed_subjects == SUBJECT_COUNT)
        {
            all_pass_count++;
        }
    }

    for (size_t student_index = 0;
         student_index < student_count;
         student_index++)
    {
        for (size_t subject_index = 0;
             subject_index < SUBJECT_COUNT;
             subject_index++)
        {
            subject_sums[subject_index] +=
                students[student_index].scores[subject_index];
        }
    }

    for (size_t subject_index = 1;
         subject_index < SUBJECT_COUNT;
         subject_index++)
    {
        if (subject_sums[subject_index] <
            subject_sums[hardest_subject])
        {
            hardest_subject = subject_index;
        }
    }

    printf("\nSubject averages:\n");

    for (size_t subject_index = 0;
         subject_index < SUBJECT_COUNT;
         subject_index++)
    {
        printf("Subject %zu average: %.2f\n",
               subject_index + 1,
               subject_sums[subject_index] /
                   (double)student_count);
    }

    printf("\nClass average: %.2f\n",
           sum / (double)student_count);

    printf("Top student: %s, %.2f\n",
           students[best_index].name,
           students[best_index].average);

    printf("Lowest student: %s, %.2f\n",
           students[lowest_index].name,
           students[lowest_index].average);

    printf("Hardest subject: %zu, average: %.2f\n",
           hardest_subject + 1,
           subject_sums[hardest_subject] /
               (double)student_count);

    printf("Students with average >= 85: %d\n", count);

    printf("Students who passed all subjects: %d\n",
           all_pass_count);

    return 0;
}