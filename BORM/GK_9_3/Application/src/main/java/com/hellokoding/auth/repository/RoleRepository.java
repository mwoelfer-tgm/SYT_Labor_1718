package main.java.com.hellokoding.auth.repository;

import main.java.com.hellokoding.auth.model.Role;
import org.springframework.data.jpa.repository.JpaRepository;

public interface RoleRepository extends JpaRepository<Role, Long>{
}
