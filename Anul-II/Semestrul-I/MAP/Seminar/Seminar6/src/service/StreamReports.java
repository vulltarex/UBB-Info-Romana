package service;

import domain.Grade;
import domain.Homework;
import domain.Student;

import java.util.Comparator;
import java.util.List;
import java.util.Locale;
import java.util.Objects;

public class StreamReports {
    public StreamReports() {}

    public static double getAvg(Student s, List<Grade> grades) {
        return grades.stream()
                .filter(g -> Objects.equals(g.getStudent().getId(), s.getId()))
                .mapToDouble(Grade::getValue)
                .average()
                .orElse(1.1);
    }

    public static double getAvgTeacher(List<Grade> grades, String teacher) {
        return grades.stream()
                .filter(g -> g.getTeacher().equals(teacher))
                .mapToDouble(Grade::getValue)
                .average()
                .orElse(0.0);
    }

    public static long getStudentCount(List<Grade> grades, Homework homework, int group) {
        return grades.stream()
                .filter(g -> g.getHomework().getId().equals(homework.getId()))
                .filter(g -> g.getStudent().getGroup() == group)
                .map(g -> g.getStudent().getId())
                .distinct()
                .count();
    }

    public static List<Student> studentsByNameAndAvg(List<Student> students, List<Grade> grades, String text) {
        return students.stream()
                .filter(s -> s.getName().toLowerCase(Locale.ROOT).contains(text.toLowerCase(Locale.ROOT)))
                .sorted(Comparator.comparingDouble( (Student s) -> getAvg(s, grades) )
                        .reversed().thenComparing(Student::getName))
                .toList();
    }

    public static List<String> teacherByNameAndAvg(List<Grade> grades, String text) {
        return grades.stream()
                .map(Grade::getTeacher)
                .distinct()
                .filter(t -> t.toLowerCase(Locale.ROOT).contains(text.toLowerCase(Locale.ROOT)))
                .sorted(Comparator.comparingDouble( (String t) -> getAvgTeacher(grades, t) )
                        .reversed())
                .toList();
    }

    public static List<Homework> groupHomework(List<Grade> grades, List<Homework> homeworkList, int group) {
        return homeworkList.stream()
                .sorted(Comparator.comparingLong( (Homework h) -> getStudentCount(grades, h, group) )
                        .reversed())
                .toList();
    }
}
