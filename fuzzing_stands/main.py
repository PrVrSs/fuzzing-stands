import docker
import logging
from pathlib import Path


class Stand:
    def __init__(self):
        self._client = docker.from_env()

    def build_images(self, stand: Path):
        self._client.images.build(str(stand))

    def run(self):
        self._client.containers.run(
            'qwerty',
            detach=True,
            name='test_qwerty2',
            ports={'5001/tcp': 3333},
        )

    def stop(self, identifier: str):
        container = self._client.containers.get(identifier)

        if container.status == 'running':
            logging.info('Stop container %s' % container)
            container.stop()
        else:
            logging.warning(
                'Container %s are in %s state' % (container, container.status))

    def remove(self, identifier: str):
        container = self._client.containers.get(identifier)

        logging.info('Remove container %s' % container)
        container.remove()

    def __enter__(self):
        self.run()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.stop('test_qwerty2')
        self.remove('test_qwerty2')


def main():
    logging.getLogger('').setLevel('INFO')

    with Stand() as stand:
        pass


if __name__ == '__main__':
    main()
