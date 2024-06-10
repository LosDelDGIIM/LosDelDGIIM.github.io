module Primero
	class Padre

		def metodoPublico(p)
			metodoPrivado
			#p.metodoPrivado
			metodoProtegido
			p.metodoProtegido
		end

		private
		def metodoPrivado
		end

		protected
		def metodoProtegido
		end
	end

end

module Segundo
	class Hija < Primero::Padre

		def metodoPublico(p)
			metodoPrivado
			#p.metodoPrivado
			metodoProtegido
			p.metodoProtegido
		end

	end
end

Primero::Padre.new.metodoPublico(Segundo::Hija.new)
Segundo::Hija.new.metodoPublico(Primero::Padre.new)
