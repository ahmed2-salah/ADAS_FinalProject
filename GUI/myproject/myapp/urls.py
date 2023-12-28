# myapp/urls.py
from django.urls import path
from .views import TemperatureView, receive_data

urlpatterns = [
    path('temperature/', TemperatureView.as_view(), name='temperature_view'),
    # Add other URLs as needed
    path('receive_data/', receive_data, name='receive_data'),

]
