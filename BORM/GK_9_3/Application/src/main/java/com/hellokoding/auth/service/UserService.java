package main.java.com.hellokoding.auth.service;

import main.java.com.hellokoding.auth.model.User;

public interface UserService {
    void save(User user);

    User findByUsername(String username);
}
