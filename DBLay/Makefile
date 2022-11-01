DOCKER_COMPOSE = docker-compose
DOCKER_COMPOSE_FILE = ./db.yaml

.PHONY: start down

start:
	$(DOCKER_COMPOSE) -f $(DOCKER_COMPOSE_FILE) up
down:
	$(DOCKER_COMPOSE) -f $(DOCKER_COMPOSE_FILE) down