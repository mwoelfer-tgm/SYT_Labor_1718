package test.java.com.hellokoding.auth.test;
/*
* Copyright 2012-2017 the original author or authors.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

import main.java.com.hellokoding.auth.repository.UserRepository;
import main.java.com.hellokoding.auth.*;
import main.java.com.hellokoding.auth.repository.*;
import org.junit.Test;
import org.junit.runner.RunWith;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.ActiveProfiles;
import org.springframework.test.context.TestPropertySource;
import org.springframework.test.context.junit4.SpringRunner;
import static org.assertj.core.api.Assertions.assertThat;
import main.java.com.hellokoding.auth.model.User;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = {WebApplication.class, UserRepository.class})
// Enable JMX so we can test the MBeans (you can't do this in a properties file)
@TestPropertySource(properties = { "spring.jmx.enabled:true",
		"spring.datasource.jmx-enabled:true" })
@ActiveProfiles("scratch")
// Separate profile for web tests to avoid clashing databases
public class UserTest {
 
    @Autowired
    private UserRepository userRepository;
    
    @Autowired
    private TestEntityManager entityManager;
 
    // write test cases here
    
    @Test
    public void whenFindByName_thenReturnUser() {
        // given
        User u = new User();
        u.setUsername("mwoelfer01");
        entityManager.persist(u);
        entityManager.flush();
     
        // when
        User found = userRepository.findByUsername(u.getUsername());
     
        // then
        System.out.println(found.getUsername());
        assertThat(found.getUsername())
          .isEqualTo(u.getUsername());
    }
    
}