plugins {
    java
    application
}

group = "ro.ubbcluj.cs.map"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    implementation("org.postgresql:postgresql:42.7.7")
}

sourceSets {
    main {
        java {
            srcDirs("src")
            exclude("main/resources/**")
        }
    }
    test {
        java {
            srcDirs("test")
        }
    }
}

application {
    mainClass.set("Main")
}

tasks.withType<JavaCompile> {
    options.encoding = "UTF-8"
}
