    
FROM nginx:1.20

RUN rm /etc/nginx/nginx.conf
COPY nginx.conf /etc/nginx/
RUN rm /etc/nginx/conf.d/default.conf
COPY project.conf /etc/nginx/conf.d/

# RUN firewall-cmd --zone=public --add-service=http --permanent
# RUN firewall-cmd --reload