package main.java.com.hellokoding.auth.repository;

import main.java.com.hellokoding.auth.model.User;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, Long> {
    User findByUsername(String username);
}
