from django.shortcuts import render
# myapp/views.py
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.views import View
import json
from .models import TemperatureReading

@method_decorator(csrf_exempt, name='dispatch')
class TemperatureView(View):
    def post(self, request, *args, **kwargs):
        data = json.loads(request.body.decode('utf-8'))
        temperature_value = data.get('temperature', None)

        if temperature_value is not None:
            # Save temperature reading to the database
            TemperatureReading.objects.create(value=temperature_value)
            return JsonResponse({'status': 'success'})
        else:
            return JsonResponse({'status': 'error', 'message': 'Temperature data not provided'}, status=400)
@csrf_exempt  # Disabling CSRF for simplicity. In production, use a proper CSRF protection.
def receive_data(request):
    if request.method == 'GET':
        data = request.GET.get('data', '')
        if data:
            with open('data.txt', 'a') as file:
                file.write(data + '\n')
            return HttpResponse(' abo gabal am el magal Data received and stored successfully.')
        else:
            return HttpResponse('No data received.')
    else:
        return HttpResponse('Invalid request method.')
# Create your views here.

    #python manage.py runserver 0.0.0.0:8000