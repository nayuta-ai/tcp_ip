IMAGE_NAME=tcp_ip
CONTAINER_NAME=tcp_ip
FORCE_RM=true
SHM_SIZE=2g

stop:
	docker stop $(CONTAINER_NAME)

build:
	docker build \
		-f docker/Dockerfile \
		-t $(IMAGE_NAME) \
		--no-cache \
		--force-rm=$(FORCE_RM) \
		.
run:
	docker run \
		-dit \
		-v $$(PWD):/workspace \
		--name $(CONTAINER_NAME) \
		--privileged \
		--rm \
		--shm-size $(SHM_SIZE) \
		$(IMAGE_NAME)
exec:
	docker exec \
	  -it \
  	$(CONTAINER_NAME) bash