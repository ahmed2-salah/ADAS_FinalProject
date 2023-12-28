from django.db import models


class TemperatureReading(models.Model):
    value = models.FloatField()
    timestamp = models.DateTimeField(auto_now_add=True)
    print(value)
    def __str__(self):
        return f'Temperature Reading: {self.value} at {self.timestamp}'

# Create your models here.
