class Timer

  def initialize
    @start = Time.now
  end

  def millis
    ((Time.now - @start) * 1000).to_i
  end

  def to_s
    diff = millis()

    hours = (diff / 1000) / 3600
    minutes = (diff / 1000 % 3600) / 60
    seconds = (diff / 1000) % 60
    hundredths = (diff % 1000) / 10

    if hours > 0
      output = '%2d:%02d:%02d hours' % [hours, minutes, seconds]
    elsif minutes > 0
      output = '%2d:%02d minutes' %[minutes, seconds]
    else
      output = '%2d.%02d seconds' %[seconds, hundredths]
    end
  end

end