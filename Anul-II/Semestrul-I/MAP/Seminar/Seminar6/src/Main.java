import domain.Grade;
import domain.Homework;
import domain.Student;
import service.StreamReports;

import java.time.LocalDate;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Stream;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    private static List<Student> getStudents() {
        Student s1 = new Student("andrei", 221);
        s1.setId(1L);
        Student s2 = new Student("dan", 222);
        s2.setId(2L);
        Student s3 = new Student("gigi", 221);
        s3.setId(3L);
        Student s4 = new Student("costel", 222);
        s4.setId(4L);
        return Arrays.asList(s1, s2, s3, s4);
    }

    private static List<Homework> getHomeworks() {
        return Arrays.asList(
                new Homework("t1", "desc1"),
                new Homework("t2", "desc2"),
                new Homework("t3", "desc3"),
                new Homework("t4", "desc4")
        );
    }

    private static List<Grade> getGrades(List<Student> stud, List<Homework> homeworks) {
        return Arrays.asList(
                new Grade(stud.get(0), homeworks.get(0), 10d, LocalDate.of(2019, 11, 2), "profesor1"),
				new Grade(stud.get(0), homeworks.get(1), 10d, LocalDate.of(2019, 11, 2), "profesor2"),
                new Grade(stud.get(1), homeworks.get(0), 9d, LocalDate.of(2019, 11, 2).minusWeeks(1), "profesor1"),
                new Grade(stud.get(1), homeworks.get(1), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Grade(stud.get(1), homeworks.get(2), 10d, LocalDate.of(2019, 10, 20), "profesor2"),
                new Grade(stud.get(2), homeworks.get(1), 7d, LocalDate.of(2019, 10, 28), "profesor1"),
                new Grade(stud.get(2), homeworks.get(3), 9d, LocalDate.of(2019, 10, 27), "profesor2"),
                new Grade(stud.get(1), homeworks.get(3), 10d, LocalDate.of(2019, 10, 29), "profesor2")
        );
    }
    public static void main(String[] args) {
        List<Grade> grades = getGrades(getStudents(), getHomeworks());
        //grades.forEach(System.out::println);
        List<Student> students = getStudents();
        List<Homework> homeworkList = getHomeworks();

        StreamReports.studentsByNameAndAvg(students, grades, "a")
                .forEach(s -> System.out.println(s + " media: " + StreamReports.getAvg(s, grades)));

        StreamReports.teacherByNameAndAvg(grades, "1")
                .forEach(t -> System.out.println(t + " media notelor date: " + StreamReports.getAvgTeacher(grades, t)));

        StreamReports.groupHomework(grades, homeworkList, 222).forEach(h ->
                System.out.println(h.getId() + " " + StreamReports.getStudentCount(grades, h, 222)));
    }
}