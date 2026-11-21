FROM fluent/fluentd:v1.17-debian-1
USER root
RUN gem install elasticsearch -v 8.15.0 --no-document \
 && gem install fluent-plugin-elasticsearch -v 5.4.3 --no-document
COPY fluent.conf /fluentd/etc/fluent.conf
USER fluent
