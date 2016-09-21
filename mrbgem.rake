MRuby::Gem::Specification.new('mruby-capp') do |spec|
  spec.license = 'MIT'
  spec.author  = 'Eric Hodel'

  spec.linker.libraries << 'pcap'

  spec.add_test_dependency 'mruby-mtest'
end
