# myproject/urls.py
from django.contrib import admin
from django.urls import include, path

from myproject.myapp.views import receive_data

urlpatterns = [
    path('admin/', admin.site.urls),
 
    path('receive_data/', receive_data, name='receive_data'),
    path('myapp/', include('myapp.urls')),  # Include your app's URLs
]

    #python manage.py runserver 0.0.0.0:8000